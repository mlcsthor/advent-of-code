{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = [ 
    pkgs.git 
    pkgs.nixpkgs-fmt  
  ];

  languages.cplusplus.enable = true;
}
