clear

data_dir = "raw_csv_data/0420_0459PM0/0420_0459PM0.csv";

data = csvread(data_dir);
[data_num, sample_num] = size(data);

for i = 2:1:data_num
    figure(i)
    plot(data(1,:), data(i,:))
end

