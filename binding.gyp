{
  "targets": [
    {
      "target_name": "matlab",
      "sources": ["src/main.cpp"],
      "cflags": ["-Wall", "-std=c++11"],
      "include_dirs" : ['./include', "<!(node -e \"require('nan')\")"],
      "libraries": [ "<(module_root_dir)/lib/libmx.lib", "<(module_root_dir)/lib/libmex.lib", "<(module_root_dir)//lib/libeng.lib" ],
    }
  ]
}