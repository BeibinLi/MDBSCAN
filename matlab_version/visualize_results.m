
function [] = visualize_results(filename) 
% This function will plot two graphs: the original data & the fixations 
% identified by MDBSCAN algorithm. The fixations will be drawn in 5 different
% colors.
% Sample usage: visualize_results('1.out')
marker_size = 10;

data = load(filename);
temp = find( data(:,2) < 1200);
data = data(temp, :);
data = [data;   0 0 0 -1  ]; % include the origin

figure; axis equal; % Plot the original data.
plot(data(:,1),data(:,2), 'k.', 'MarkerSize',marker_size);

figure;  axis equal;

% Plot every point just in White Color
plot(data(:,1),data(:,2),'w.', 'MarkerSize',marker_size);
hold on;
colors = ['r','y','b','g','c'];

data(:,4) = data(:,4) + 1;
num_fixations = max(data(:,4));
fixation_lengths = zeros(num_fixations, 1);

for ID=1:num_fixations, % fixation ID
    % draw different fixations
    
    fixation_lengths(ID) = size(find(data(:,4) == ID), 1);
    p = find(data(:,4) == ID); % [ point index ] that are in the fixation
    s = data(p', :); % coordinates of the points in p
    plot(s(:,1),s(:,2),strcat('.', colors(mod(ID, size(colors,2))+1)), 'MarkerSize',marker_size);
end

end