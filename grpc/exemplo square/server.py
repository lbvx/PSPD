import grpc
from concurrent import futures
import time
import square_pb2
import square_pb2_grpc

class SquareServicer(square_pb2_grpc.SquareServiceServicer):
    def GetSquare(self, request, context):
        result = request.number ** 2
        return square_pb2.SquareResponse(result=result)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    square_pb2_grpc.add_SquareServiceServicer_to_server(SquareServicer(), server)
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started. Listening on port 50051.")
    try:
        while True:
            time.sleep(86400)
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()
