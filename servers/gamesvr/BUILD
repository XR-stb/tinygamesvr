load("//common:common_build_vars.bzl", "default_copts")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# cc_library(
#     name = "gamesvr_deps",
#     visibility = ["//visivility:public"],
#     deps = [

#     ],
# )

cc_binary(
    name = "gamesvr",
    srcs = glob(["**/*.h", "**/*.cpp"]),
    copts = default_copts,
    deps = [
        "//protocol:protoconf",
        "@com_google_protobuf//:protobuf",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
    ],
)

