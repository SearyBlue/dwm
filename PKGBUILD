pkgname=dwm-kirito
gitname=dwm
pkgver=6.2
pkgrel=1
pkgdesc='Dynamic Window Manager for X'
arch=('x86_64')
source=('git+https://github.com/SearyBlue/dwm')
sha1sums=('SKIP')
provides=('dwm')
conflicts=('dwm' 'dwm-git')

build() 
{
	cd "$srcdir/$gitname"
	cat /home/kirito/.config/dwm/config.h > config.h
	make
}

package() 
{
  	cd "$srcdir/$gitname"
  	make PREFIX=/usr DESTDIR="${pkgdir}" install
}
