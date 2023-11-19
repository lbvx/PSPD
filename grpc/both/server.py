import grpc
from concurrent import futures
import time
import both_pb2
import both_pb2_grpc

class BothServicer(both_pb2_grpc.BothServiceServicer):
    def GetSquare(self, request, context):
        result = request.number ** 2
        return both_pb2.SquareResponse(result=result)

    def GetCube(self, request, context):
        result = request.number ** 3
        return both_pb2.CubeResponse(result=result)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    both_pb2_grpc.add_BothServiceServicer_to_server(BothServicer(), server)
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
