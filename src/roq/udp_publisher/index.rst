.. _roq-udp-publisher:

roq-udp-publisher
=================

UDP (multicast) publisher

The publisher allows you transmit :cpp:class:`CustomMetrics` over UDP (multicast).


Installing
----------

* :ref:`Using Conda <tutorial-conda>`

.. tab:: Unstable

  .. code-block:: shell

     $ conda install \
           --channel https://roq-trading.com/conda/unstable \
           roq-udp-publisher

.. tab:: Stable

  .. code-block:: shell

     $ conda install \
           --channel https://roq-trading.com/conda/stable \
           roq-udp-publisher


Using
-----

.. code-block:: shell

   $ roq-udp-publisher \
         --name "udp-publisher" \
         --config_file $CONFIG_FILE_PATH \
         --client_listen_address $UNIX_SOCKET_PATH \
         --flagfile $ENVIRONMENT_FLAGFILE


.. _roq-udp-publisher-flags:

Flags
-----

* :ref:`Using Flags <abseil-cpp>`
* :ref:`Gateway Flags <gateway-flags>`

.. code-block:: shell

   $ roq-udp-publisher --help

.. tab:: Flags

   .. include:: flags/flags.rstinc


Configuration
-------------

* :ref:`Gateway Config <gateway-config>`

.. code-block:: shell

   $ --config_file $CONDA_PREFIX/share/roq-udp-publisher/config.toml

.. important::

   The template will be replaced when the software is upgraded.
   Make a copy and modify to your needs.

.. include:: config.toml
   :code: toml


Constraints
-----------
