; reverse.scm - Task 4: Reverse a list using cond, append, cdr, car, and cons

(define (reverse lst)
  (cond ((null? lst) '())
        (else (append (reverse (cdr lst)) (list (car lst))))))

(define (display-reverse lst)
  (display "(")
  (let loop ((lst lst))
    (cond ((null? lst) (display ")"))
          ((null? (cdr lst)) (display (car lst)) (display ")"))
          (else (display (car lst)) (display " ") (loop (cdr lst))))))
