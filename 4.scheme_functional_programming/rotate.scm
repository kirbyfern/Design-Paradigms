; rotate.scm - Task 3: Purely functional rotations of a list

(define (rotate lst)
  (define (rotate-helper lst acc)
    (if (null? lst)
        acc
        (rotate-helper (append (cdr lst) (list (car lst)))
                       (append acc (list lst)))))
  (rotate-helper lst '()))
