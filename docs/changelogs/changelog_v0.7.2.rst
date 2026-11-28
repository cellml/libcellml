libCellML v0.7.2 Changelog
==========================

Bug
---

* Fix parsing of connections where variables have the same name in different components by `@hsorby <https://github.com/hsorby>`_ [`#1500 <https://github.com/cellml/libcellml/pull/1500>`_].
* Units: a reference to imported units keeps its exponent by `@FinbarArgus <https://github.com/FinbarArgus>`_ [`#1498 <https://github.com/cellml/libcellml/pull/1498>`_].
* Analyser unit check raises the multiplier of a unit to its exponent, in contrast to the specification and Units::scalingFactor by `@agarny <https://github.com/agarny>`_ [`#1467 <https://github.com/cellml/libcellml/pull/1467>`_].

Generator
---------

* Resolve unary minus code generation issue by `@hsorby <https://github.com/hsorby>`_ [`#1468 <https://github.com/cellml/libcellml/pull/1468>`_].
* Analyser/Generator: use full precision for Euler's number and π by `@agarny <https://github.com/agarny>`_ [`#1484 <https://github.com/cellml/libcellml/pull/1484>`_].

Infrastructure
--------------

* Add support for Python 3.15 by `@hsorby <https://github.com/hsorby>`_ [`#1471 <https://github.com/cellml/libcellml/pull/1471>`_].
* Fix the Windows Python wheel generation by `@hsorby <https://github.com/hsorby>`_ [`#1461 <https://github.com/cellml/libcellml/pull/1461>`_].

Miscellaneous
-------------

* Inline global constants and simplify issue lookup by `@agarny <https://github.com/agarny>`_ [`#1475 <https://github.com/cellml/libcellml/pull/1475>`_].

Contributors
------------

.. image:: https://avatars.githubusercontent.com/u/64084030?v=4
   :target: https://github.com/FinbarArgus
   :height: 32
   :width: 32
.. image:: https://avatars.githubusercontent.com/u/602265?v=4
   :target: https://github.com/agarny
   :height: 32
   :width: 32
.. image:: https://avatars.githubusercontent.com/u/778048?v=4
   :target: https://github.com/hsorby
   :height: 32
   :width: 32
