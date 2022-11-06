{ pkgs }: {
	deps = [
		pkgs.apk-tools
  pkgs.sudo
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}