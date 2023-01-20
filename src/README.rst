``llvm-cov``
============

We make extensive use of weak pointers, which means that before using them we should always check that they still hold a valid reference to an object.
In other words, we should do something like:

.. code-block:: c++

   auto sharedPtr = weakPtr.lock();

   if (sharedPtr != nullptr) {
       ...
   }

However, in the libCellML codebase, 99.9% of those tests always evaluate to ``true``, which means that ``llvm-cov`` will complain about the ``false`` never being reached while it is just us being "careful" by testing for ``sharedPtr != nullptr``.
One way to address this problem is to use a C macro:

.. code-block:: c++

   #ifdef LLVM_COVERAGE
   #    define VALID_SHARED_PTR(ptr) (true)
   #else
   #    define VALID_SHARED_PTR(ptr) (ptr != nullptr)
   #endif

It works fine, but... it's a C macro and we really don't want to go that route, not to mention that it relies on conditional compilation which is not great either.
Yet, we want 100% branch coverage with ``llvm-cov``.
So, instead, we have decided not to test for ``sharedPtr != nullptr``.
