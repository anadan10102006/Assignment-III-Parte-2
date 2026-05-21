FROM japeto/so-tools:v64

WORKDIR /app

COPY . .

RUN g++ -std=c++17 -O2 -o diskScheduler \
    main.cpp fcfs.cpp scan.cpp cscan.cpp

EXPOSE 8080

ENTRYPOINT ["sh", "entrypoint.sh"]