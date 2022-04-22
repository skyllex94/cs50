-- write a SQL query to determine the average rating of all movies released in 2012
-- SELECT AVG(rating) FROM ratings WHERE movie_id = (SELECT id FROM movies WHERE year = 2012)
SELECT AVG(rating) FROM ratings LEFT JOIN movies ON ratings.movie_id = movies.id WHERE year = 2012