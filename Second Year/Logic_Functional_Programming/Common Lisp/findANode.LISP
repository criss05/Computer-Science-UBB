(defun left_subtree (tree nv ne)
  (cond
      ((null tree) nil)
      ((= nv (+ 1 ne)) nil)
      (t (cons (car tree) (cons (cadr tree) (left_subtree (cddr tree) (+ 1 nv) (+ ne (cadr tree))))))
  )
)


(defun right_subtree (tree nv ne)
  (cond
      ((null tree) nil)
      ((= nv (+ 1 ne)) tree)
      (t (right_subtree (cddr tree) (+ 1 nv) (+ ne (cadr tree))))
  )
)


(defun left (tree) (left_subtree (cddr tree) 0 0))
(defun right (tree) (right_subtree (cddr tree) 0 0))

(defun findPath(tree x path)
  (cond 
     ((null tree) nil)
     ((equal (car tree) x) path)
     (t (append (findPath (left tree) x (append path (list (car tree)))) (findPath (right tree) x (append path (list (car tree))))))
  )
)

(defun main(tree x) (append (findPath tree x ()) (list x)))
