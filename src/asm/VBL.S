
	xdef	_vbl_isr
	xref	_vbl_request

_vbl_isr:
	movem.l	d0/a0,-(sp)
	jsr     _vbl_request
	movem.l	(sp)+,d0/a0
	rte
