import grpc
from concurrent import futures
import time
import cube_pb2
import cube_pb2_grpc

class CubeServicer(cube_pb2_grpc.CubeServiceServicer):
    def GetCube(self, request, context):
        result = request.number ** 3
        return cube_pb2.CubeResponse(result=result)

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    cube_pb2_grpc.add_CubeServiceServicer_to_server(CubeServicer(), server)
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
