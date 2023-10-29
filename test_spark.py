# Import necessary PySpark modules
from pyspark.sql import SparkSession
from pyspark.sql.functions import col

# Create a Spark session
spark = SparkSession.builder.appName("PySparkExample").getOrCreate()

# Sample data as a list of dictionaries
data = [
    {"name": "Alice", "age": 30},
    {"name": "Bob", "age": 25},
    {"name": "Charlie", "age": 35},
    {"name": "David", "age": 28}
]

# Create a DataFrame from the sample data
df = spark.createDataFrame(data)

# Show the DataFrame
df.show()

# Filter and display people with age greater than 30
df.filter(col("age") > 30).show()

# Calculate and show the average age
avg_age = df.agg({"age": "avg"}).collect()[0][0]
print(f"Average Age: {avg_age}")

# Stop the Spark session
spark.stop()
