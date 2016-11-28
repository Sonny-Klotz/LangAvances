(defun rever (liste)
	(if (null liste)
		nil
		(append (rever (cdr liste)) (list (car liste)))
	)
)
; on concatene le premier elt à la fin de la liste
; en cours on a vu cons pour concaténer, le résultat obtenu est legerement
; different pcq la fonction est particuliere.
; les deux args de append doivent etre des listes
