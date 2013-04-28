

tc = rtt.getTC()
depl = tc:getPeer("Deployer")
depl:import("ocl")
depl:import("URRealTime")

depl:loadComponent("urrealtime", "URRealTime")
ur = depl:getPeer("urrealtime")
ur:configure()
ur:start()


