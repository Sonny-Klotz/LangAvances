;caractere en lisp : #\c
;si c'est des listes, il faut comparer element par element
;sinon, on compare les valeurs directement

(defun mon-equal (x y)
	(cond 
		((and (numberp x) (numberp y)) (= x y))
		((and (characterp x) (characterp y)) (char= x y))
		((and (symbolp x) (symbolp y)) (eq x y))
		((and (stringp x) (stringp y)) (string= x y))
		((and (listp x) (listp y))
			(cond
				((and (null x) (not (null y))) nil)
				((and (not (null x)) (null y)) nil)
				((and (null x) (null y)) t)
				(t (and (mon-equal (car x) (car y)) (mon-equal (cdr x) (cdr y))))
			)
		)
		(t nil)
	)
)

