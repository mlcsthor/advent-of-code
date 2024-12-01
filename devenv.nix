{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = [
    pkgs.git
    pkgs.nixpkgs-fmt
    pkgs.go-task
  ];

  languages.cplusplus.enable = true;
}
