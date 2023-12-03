; Task 1: Tail-recursive version of integer log, base 2
(define (log2 n)
  (if (= n 1)
      0
      (+ 1 (log2 (quotient (+ n 1) 2)))))

; Task 2: Purely functional filter function
(define (filter pred lst)
  (cond ((null? lst) '())
        ((pred (car lst))
         (cons (car lst) (filter pred (cdr lst))))
        (else (filter pred (cdr lst)))))

; Task 3: Purely functional rotations of a list
(define (rotate lst)
  (if (null? lst)
      '()
      (cons lst (rotate (append (cdr lst) (list (car lst)))))))

; Task 4: Reverse a list using cond, append, cdr, car, and cons
(define (reverse lst)
  (cond ((null? lst) '())
        (else (append (reverse (cdr lst)) (list (car lst))))))

; Helper function for Task 2: Predicate function
(define (lt-than-5 x)
  (< x 5))

; Display function for Task 2
(define (display-list lst)
  (display "(")
  (let loop ((lst lst))
    (cond ((null? lst) (display ")"))
          ((null? (cdr lst)) (display (car lst)) (display ")"))
          (else (display (car lst)) (display " ") (loop (cdr lst))))))

; Example usage
(display "Task 1: log2(10) = ")
(display (log2 10))
(newline)

(display "Task 2: ")
(display-list (filter lt-than-5 '(3 9 5 8 2 4 7)))
(newline)

(display "Task 3: ")
(display-list (rotate '(a b c d e)))
(newline)

(display "Task 4: ")
(display-list (reverse '(A B B C D D E F G G)))
(newline)
