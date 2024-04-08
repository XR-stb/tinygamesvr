#!/usr/bin/env python3

import argparse

# import argcomplete

import sys
import os

# 导入其他任意路径下的py模块
project_root = os.path.dirname(os.path.abspath(__file__))
sys.path.append(project_root + "/scripts/python")
try:
    import util
except:
    pass

def get_cpp_servers():
    return util.get_directories("./servers/")

def get_golang_servers():
    return util.get_directories("./golang/cloud/cmd/")

class Make:
    def __init__(self, args):
        self.args = args
        self.cpp_targets = get_cpp_servers()
        self.golang_targets = get_golang_servers()
        self.all_targets = self.cpp_targets + self.golang_targets

    def run(self):
        # 反射到成员函数上进行调用，注意起名规范
        action = "_" + self.args.action + "_"
        getattr(self, action)()

    def build_targets(self, targets):
        for target in targets:
            if target in self.golang_targets:
                util.exec_cmd("cd golang/cloud && go build -o ../../build/golang ./cmd/%s" % target)
                continue
            if target in self.cpp_targets:
                if self.args.with_cmake:
                    util.exec_cmd("cmake --build . --target %s" % target)
                else:
                    util.exec_cmd(
                        "bazel build //servers/%s:%s --symlink_prefix=build/bazel/"
                        % (target, target)
                    )
                continue
            raise Exception("unkown tartget: %s" % target)
        
    def _build_(self):
        targets = self.args.targets
        if targets == "all" or targets == ["all"]:
            self.build_targets(self.all_targets)
        else:
            self.build_targets(targets)

    def _run_(self):
        targets = self.args.targets
        if targets == "all" or targets == ["all"]:
            # TODO: 应该将分类的bin文件都输出到build/bin下去
            raise Exception("run all bin is unaccomplish!!!")

        else:
            for target in targets:
                if target in self.golang_targets:
                    util.exec_cmd("./build/golang/%s" % target)
                    continue

                if self.args.with_cmake:
                    util.exec_cmd("./build/cmake/servers/%s/%s" % (target, target))
                else:
                    util.exec_cmd(
                        "bazel run //servers/%s:%s --symlink_prefix=build/bazel/"
                        % (target, target)
                    )

    def _genproto_(self):
        util.exec_cmd("bash ./scripts/shell/gen_proto.sh")


def parse_args():
    # https://docs.python.org/zh-cn/3.6/library/argparse.html#argparse.ArgumentParser.add_argument
    parser = argparse.ArgumentParser(
        description="Unified project build script", prog="tinygamesvr"
    )
    # parser.add_argument('integers', metavar='1', type=int, nargs='+', help='an integer for the accumulator')
    # parser.add_argument('--sum', dest='accumulate', action='store_const', const=sum, default=max, help='sum the integers (default: find the max)')
    # parser.print_help()

    subparsers = parser.add_subparsers(dest="action", help="subcommand help")

    build_parser = subparsers.add_parser("build", help="build a target")
    build_parser.add_argument(
        "targets",
        help="the server name, default is all",
        default="all",
        metavar="gamesvr",
        type=str,
        nargs="*",
        choices=["all"] + get_cpp_servers() + get_golang_servers(),
    )
    build_parser.add_argument(
        "--with-cmake", # NOTE(tianbaosha): 这里使用了 - 不过在代码中读取变量使用下划线_
        action="store_true",
        help="choose build system, default is bazel",
    )

    run_parser = subparsers.add_parser("run", help="run a target")
    run_parser.add_argument(
        "targets",
        help="the server name, default is all",
        default="all",
        metavar="gamesvr",
        type=str,
        nargs="*",
        choices=["all"] + get_cpp_servers() + get_golang_servers(),
    )
    # TODO: 更合理的做法：应该统一去读取运行目录的文件，而不是去运行cmake生成的或bazel生成bin文件？
    run_parser.add_argument(
        "--with-cmake",
        action="store_true",
        help="run server, default run bazel compile bin",
    )

    proto_parser = subparsers.add_parser("genproto", help="gen proto")
    # proto_parser.add_argument("--with_golang", action="store_true", help="choose build system, default is bazel")

    # https://kislyuk.github.io/argcomplete/
    # TODO: 命令行自动补全命令, 这个autocomplete包不好下，回头弄
    # argcomplete.autocomplete(parser)
    return parser.parse_args()


def main():
    args = parse_args()
    Make(args).run()


if __name__ == "__main__":
    main()
