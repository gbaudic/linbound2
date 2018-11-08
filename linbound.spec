#
# Spec draft for linbound
#

Summary: A turn-based multiplayer shooting game in the style of Worms
Name: linbound
Version: 0.1.0
Release: 1
License: MPL
Group: Amusements/Games/Action/Shoot
Source: https://github.com/gbaudic/linbound2/archive/master.zip
URL: https://github.com/gbaudic/linbound2
Packager: Your Name <email@mail.com>
BuildRequires: libsdl2-devel, libsdl2-image-devel, libsdl2-mixer-devel, libsdl2-gfx-devel, libsdl2-net-devel, libsdl2-ttf-devel, libsqlite3-devel, tinyxml2-devel
Requires: SDL2, SDL2_ttf, SDL2_image, SDL2_net, SDL2_gfx, SDL2_mixer, libsqlite3, tinyxml2

%description
LinBound aims to be an open-source clone of the game GunBound, 
a multiplayer turn-based arcade game with a gameplay very close 
to Worms, Hedgewars or WarMUX. It is primarily targeted to Linux 
but it aims to be as cross-platform as possible. 
          
%prep
%setup -n linbound-master

%build
%configure
make

%install
make install

%files
%doc README.md AUTHORS
res/
		  
		  
%changelog
* date <email@mail.com> 
- change
