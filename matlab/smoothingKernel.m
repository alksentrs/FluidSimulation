function [value] = smoothingKernel(smoothingRadiusNormalized,distance)
ind = find(distance < 0);
distance(ind) = -distance(ind);

volume = pi * smoothingRadiusNormalized ^ 4. / 6.;
diff = smoothingRadiusNormalized-distance;
value = (diff .^ 2) / volume;

ind = find(diff < 0);
value(ind) = 0;
end

