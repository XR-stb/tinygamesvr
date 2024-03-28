import subprocess

def log(log_str):
    print(log_str)

# 执行过程不会输出到终端
def run_cmd(cmd, need_log=True, shell=True, **kwargs):
    shell_proc = subprocess.Popen([cmd], shell=shell, stdout=subprocess.PIPE, stderr=subprocess.PIPE, **kwargs)

    # https://blog.csdn.net/carolzhang8406/article/details/22286913
    # 代替wait, 避免stdout和stderr的输出内容 超过 PIPE size 时发生死锁
    stdout, stderr = shell_proc.communicate()
    ret_code = shell_proc.poll()

    if need_log:
        cmd_str = cmd if isinstance(cmd, str) else subprocess.list2cmdline(cmd)

        log_out = "ret_code: %d\n" % ret_code
        if stdout:
            log_out += 'stdout: %s\n' % stdout.decode('utf-8')
        if stderr:
            log_out += 'stderr: %s\n' % stderr.decode('utf-8')
        if ret_code == 0:
            log('run cmd success: %s' % cmd_str)
        else:
            log('run cmd failed: %s\n%s' % (cmd_str, log_out))

    return ret_code, stdout.decode('utf-8'), stderr.decode('utf-8')

# 实时打印输出
def exec_cmd(cmd, need_log=True, shell=True, **kwargs):
    shell_proc = subprocess.Popen(cmd, shell=shell, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, **kwargs)

    # 实时打印输出
    while True:
        output = shell_proc.stdout.readline()
        if shell_proc.poll() is not None and output == b'':
            break
        if output:
            log(output.decode('utf-8').strip())

    ret_code = shell_proc.poll()

    if need_log:
        cmd_str = cmd if isinstance(cmd, str) else subprocess.list2cmdline(cmd)
        if ret_code == 0:
            log('run cmd success: %s' % cmd_str)
        else:
            log('run cmd failed: %s' % cmd_str)

    return ret_code