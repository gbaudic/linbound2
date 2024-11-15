#
# Spec draft for linbound
#

Summary: A turn-based multiplayer shooting game in the style of Worms
Name: linbound2
Version: 0.1.0
Release: 1
License: MPL-2.0
Group: Amusements/Games/Action/Shoot
Source: https://github.com/gbaudic/%{name}/archive/master.zip
URL: https://github.com/gbaudic/%{name}
Packager: Gwilherm Baudic <email@mail.com>
BuildRequires: libsdl2-devel
BuildRequires: libsdl2-image-devel
BuildRequires: libsdl2-mixer-devel
BuildRequires: libsdl2-gfx-devel
BuildRequires: libsdl2-net-devel
BuildRequires: libsdl2-ttf-devel
BuildRequires: libsqlite3-devel
BuildRequires: tinyxml2-devel
BuildRequires: git
BuildRequires: scons
BuildRequires: g++
BuildRequires: cmake >= 3.9

Requires: SDL2
Requires: SDL2_ttf
Requires: SDL2_image
Requires: SDL2_net
Requires: SDL2_gfx
Requires: SDL2_mixer
Requires: libsqlite3
Requires: tinyxml2
Requires: linbound-data

%description
LinBound aims to be an open-source clone of the game GunBound, 
a multiplayer turn-based arcade game with a gameplay very close 
to Worms, Hedgewars or WarMUX. It is primarily targeted to Linux 
but it aims to be as cross-platform as possible. 

%package data
BuildArch: noarch

%package server

%description data
This package contains the game files.

%description server
This package contains the server. It is not needed unless you want to be able to host your own games.

%prep
%setup -n linbound-master
git clone https://github.com/gbaudic/guisan
pushd guisan && scons && scons install && popd

%build
cmake . -DENABLE_SERVER=ON
make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%make_install

%files
%defattr(-,root,root,-)
%doc README.md
%doc AUTHORS
%license LICENSE
%attr(755,root,root) /usr/local/bin/linbound

%files data
%defattr(-,root,root,-)
res/

%files server
%defattr(-,root,root,-)
%attr(755,root,root) /usr/local/bin/linbound_server

%changelog
* date <email@mail.com> 
- Initial version
