.. _roq-udp-publisher:

roq-udp-publisher
=================


Purpose
-------

* UDP (multicast) publisher


Description
-----------

The publisher allows you transmit :cpp:class:`CustomMetrics` over UDP (multicast).


Conda
-----

* :ref:`Using Conda <tutorial-conda>`

.. tab:: Install
  
  .. code-block:: bash
  
    $ mamba install \
      --channel https://roq-trading.com/conda/stable \
      roq-udp-publisher
  
.. tab:: Configure

  .. code-block:: bash
  
    $ cp $CONDA_PREFIX/share/roq-udp-publisher/config.toml $CONFIG_FILE_PATH
  
    # Then modify $CONFIG_FILE_PATH to match your specific configuration
  
.. tab:: Run
  
  .. code-block:: bash
  
    $ roq-udp-publisher \
          --name "udp-publisher" \
          --config_file "$CONFIG_FILE_PATH" \
          --service_listen_address "$TCP_LISTEN_PORT_FOR_METRICS" \
          --listen_address "$TCP_LISTEN_PORT_FOR_WS_CLIENTS" \
          --flagfile "$FLAG_FILE"
  

Config
------

.. tab:: Users
  
  A list of clients allowed to connect to the publisher.

  .. code-block:: toml

    [users]
   
     [users.MD1]
     username="tbmd1"


Flags
-----

* :ref:`Using Flags <abseil-cpp>`

.. code-block:: bash

   $ roq-udp-publisher --help

.. tab:: Flags

   .. include:: flags/flags.rstinc


Constraints
-----------
