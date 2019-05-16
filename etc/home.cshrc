# $FreeBSD: src/share/skel/dot.cshrc,v 1.14.10.1 2009/08/03 08:13:06 kensmith Exp $
#
# .cshrc - csh resource script, read at beginning of execution by each shell
#
# see also csh(1), environ(7).
#

alias ls ls --color=auto
alias h		history 25
alias j		jobs -l
alias la	ls -a
alias lf	ls -FA
alias ll	ls -lF
alias rm	rm -i
# A righteous umask
#umask 22

#set path = (/sbin /bin /usr/sbin /usr/bin /usr/games /usr/local/sbin /usr/local/bin $HOME/bin)

#setenv	EDITOR	vi
#setenv	PAGER	less
setenv	BLOCKSIZE	K

if ($?prompt) then
	# An interactive shell -- set some stuff up
	set filec
	set history = 1000
	set savehist = 1000
	set mail = (/var/mail/$USER)
	if ( $?tcsh ) then
		bindkey "^W" backward-delete-word
		bindkey -k up history-search-backward
		bindkey -k down history-search-forward
	endif
endif

#alias ls ls -FGa
setenv LSCOLORS gxfxcxdxFxegedabagacad
setenv CLICOLOR yes
if ( $tty =~ ttyv* ) then
setenv TERM cons25
else
setenv TERM xterm-color
endif
if ( $USER == root ) then
set prompt="%B[%n@%m %/]# "
else
set prompt="%B%{\033[36m%}%T %{\033[33m%}%n%{\033[37m%}@%m%{\033[32m%}[%~]%{\033[0m%}$ "
endif
set autolist

