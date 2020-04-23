#
#    fty-asset-activator - Library providing asset activation/deactivation functionality
#
#    Copyright (C) 2019 - 2020 Eaton
#
#    This program is free software; you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation; either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License along
#    with this program; if not, write to the Free Software Foundation, Inc.,
#    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

# To build with draft APIs, use "--with drafts" in rpmbuild for local builds or add
#   Macros:
#   %_with_drafts 1
# at the BOTTOM of the OBS prjconf
%bcond_with drafts
%if %{with drafts}
%define DRAFTS yes
%else
%define DRAFTS no
%endif
Name:           fty-asset-activator
Version:        1.0.0
Release:        1
Summary:        library providing asset activation/deactivation functionality
License:        GPL-2.0+
URL:            https://42ity.org
Source0:        %{name}-%{version}.tar.gz
Group:          System/Libraries
# Note: ghostscript is required by graphviz which is required by
#       asciidoc. On Fedora 24 the ghostscript dependencies cannot
#       be resolved automatically. Thus add working dependency here!
BuildRequires:  ghostscript
BuildRequires:  asciidoc
BuildRequires:  automake
BuildRequires:  autoconf
BuildRequires:  libtool
BuildRequires:  pkgconfig
BuildRequires:  xmlto
BuildRequires:  gcc-c++
BuildRequires:  libsodium-devel
BuildRequires:  zeromq-devel
BuildRequires:  czmq-devel >= 3.0.2
BuildRequires:  malamute-devel >= 1.0.0
BuildRequires:  fty-common-logging-devel
BuildRequires:  fty-proto-devel >= 1.0.0
BuildRequires:  cxxtools-devel
BuildRequires:  fty-common-mlm-devel
BuildRoot:      %{_tmppath}/%{name}-%{version}-build

%description
fty-asset-activator library providing asset activation/deactivation functionality.

%package -n libfty_asset_activator1
Group:          System/Libraries
Summary:        library providing asset activation/deactivation functionality shared library

%description -n libfty_asset_activator1
This package contains shared library for fty-asset-activator: library providing asset activation/deactivation functionality

%post -n libfty_asset_activator1 -p /sbin/ldconfig
%postun -n libfty_asset_activator1 -p /sbin/ldconfig

%files -n libfty_asset_activator1
%defattr(-,root,root)
%{_libdir}/libfty_asset_activator.so.*

%package devel
Summary:        library providing asset activation/deactivation functionality
Group:          System/Libraries
Requires:       libfty_asset_activator1 = %{version}
Requires:       libsodium-devel
Requires:       zeromq-devel
Requires:       czmq-devel >= 3.0.2
Requires:       malamute-devel >= 1.0.0
Requires:       fty-common-logging-devel
Requires:       fty-proto-devel >= 1.0.0
Requires:       cxxtools-devel
Requires:       fty-common-mlm-devel

%description devel
library providing asset activation/deactivation functionality development tools
This package contains development files for fty-asset-activator: library providing asset activation/deactivation functionality

%files devel
%defattr(-,root,root)
%{_includedir}/*
%{_libdir}/libfty_asset_activator.so
%{_libdir}/pkgconfig/libfty_asset_activator.pc
%{_mandir}/man3/*
%{_mandir}/man7/*

%prep

%setup -q

%build
sh autogen.sh
%{configure} --enable-drafts=%{DRAFTS}
make %{_smp_mflags}

%install
make install DESTDIR=%{buildroot} %{?_smp_mflags}

# remove static libraries
find %{buildroot} -name '*.a' | xargs rm -f
find %{buildroot} -name '*.la' | xargs rm -f


%changelog
