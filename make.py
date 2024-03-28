#!/usr/bin/env python3

import argparse
# import argcomplete

import sys
import os

# 导入其他任意路径下的py模块
project_root = os.path.dirname(os.path.abspath(__file__))
sys.path.append(project_root + '/scripts/python')
try:
    import util
except:
    pass


server_list = None

def get_servers():
    # TODO
    return ['gamesvr', 'chatsvr']

class Make:
    def __init__(self, args):
        self.args = args

    def run(self):
        action = '_' + self.args.action + '_'
        getattr(self, action)()

    def _build_(self):
        targets = self.args.targets
        if targets == 'all' or targets == ['all']:
            # TODO:
            print('all target')
        else:
            for target in targets:
                util.exec_cmd("bazel build //servers/%s:%s --symlink_prefix=build/bazel/" % (target, target))

    def _run_(self):
        targets = self.args.targets
        if targets == 'all' or targets == ['all']:
            # TODO:
            print('all target')
        else:
            for target in targets:
                util.exec_cmd("bazel run //servers/%s:%s --symlink_prefix=build/bazel/" % (target, target))            
    
def parse_args():
    global server_list
    server_list = get_servers()

    # https://docs.python.org/zh-cn/3.6/library/argparse.html#argparse.ArgumentParser.add_argument
    parser = argparse.ArgumentParser(description='Unified project build script', prog='tinygamesvr')
    # parser.add_argument('integers', metavar='1', type=int, nargs='+', help='an integer for the accumulator')
    # parser.add_argument('--sum', dest='accumulate', action='store_const', const=sum, default=max, help='sum the integers (default: find the max)')
    # parser.print_help()

    subparsers = parser.add_subparsers(dest="action", help="subcommand help")

    build_parser = subparsers.add_parser('build', help='build a target')
    build_parser.add_argument("targets", help="the server name, default is all", default='all', 
                              metavar='gamesvr', type=str, nargs='*', choices=['all'] + server_list)
    
    run_parser = subparsers.add_parser('run', help='run a target')
    run_parser.add_argument("targets", help="the server name, default is all", default='all', 
                              metavar='gamesvr', type=str, nargs='*', choices=['all'] + server_list)

    # Command line completion
    # argcomplete.autocomplete(parser)
    return parser.parse_args()

def main():
    args = parse_args()
    Make(args).run()

if __name__ == '__main__':
    main()