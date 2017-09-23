%%
% Find the index of the closest value in a given array
% 
%
function [idx] = find_nearest(target_val, source_matrix, start_search_pos, ...
                              MAX_BACK_SEARCH, MAX_FRONT_SEARCH)
  % Allowable Noise Coefficients
  %
  % Setting these too large will cause the algorithm to jump around
  % Setting these too small will cause the algorithm to get stuck in a minima or maxima
  % The larger of these two values is the bias the algorithm will try to reconstruct
  % For example, if MAX_FRONT_SEARCH is bigger, then the trend will be 
  % to advance the slide FORWARD
  %
  %
  % Find all places in the source array it could be
  search_array = [];
  if(target_val > source_matrix(start_search_pos))
    search_array = find(source_matrix >= target_val);
  else  
    search_array = find(source_matrix <= target_val);
  end

  % Only move forward
  potential_matches = search_array > (start_search_pos - MAX_BACK_SEARCH) ...
                    & search_array < (start_search_pos + MAX_FRONT_SEARCH);
  idx = search_array(find(potential_matches, 1));
  if isempty(idx)
    idx = start_search_pos;
  end  
  
  assert(idx >= (start_search_pos - MAX_BACK_SEARCH));
