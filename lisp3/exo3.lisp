(defun pos+_rec (liste)
	(if (or (not (listp liste)) (null liste))
		nil
		(and 
			(numberp (car liste))
			(cons (+  indice (car liste)) (pos+_rec (cdr liste))) ;recupérer l'indice de l'elt
		)
	)
)

;solutions
;1 - fct auxiliaire (indice liste) : pas efficace O(|liste|²)
;2 - deuxieme argument indice (actuel), modif le prototype de la fonction
;3 - la liste est déf globalement (- (list-length **liste**) (list-length liste)) => calcul de l'indice

(defun pos+_it (liste)
	(if (or (not (listp liste)) (null liste))
		nil
		(let (x)
			(do ((i 0 (+ i 1)) (tmp liste (cdr tmp)))
				((null tmp) x)
				(if (numberp (car tmp))
					(setf x (append x (list (+ i (car tmp)))))
					(progn
						(format t "~A not a number" (car tmp))
						(return 'error)
					)
				)
			)
		)
	)
)
