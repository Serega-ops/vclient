# vclient — сетевой клиент (курсовая, ТиМП, ПГУ)

## Сборка
    sudo apt install libboost-all-dev libcrypto++-dev cmake g++
    cmake -B build && cmake --build build

## Запуск
    ./build/vclient -a 127.0.0.1 -i input.txt -o result.bin -c ~/.config/vclient.conf

## Параметры
    -a, --address  адрес сервера (обязательный)
    -p, --port     порт (по умолчанию 33333)
    -i, --input    файл исходных данных (обязательный)
    -o, --output   файл результатов (обязательный)
    -c, --config   файл LOGIN:PASSWORD (по умолчанию ~/.config/vclient.conf)
    -h, --help     справка
