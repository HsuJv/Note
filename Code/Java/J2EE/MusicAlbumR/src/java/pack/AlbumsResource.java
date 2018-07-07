/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pack;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.URI;
import javax.ws.rs.Produces;
import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PUT;
import javax.ws.rs.PathParam;
import javax.ws.rs.WebApplicationException;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.StreamingOutput;

/**
 * REST Web Service
 *
 * @author Hsu
 */
@Path("albums")
public class AlbumsResource {

    BuildAlbums buildAlbum = new BuildAlbums();

    @POST
    @Consumes("application/xml")
    public Response addAlbum(InputStream albumData) {
        try {
            Albums albums = buildAlbum.parseAlbum(null, albumData);
            String albumId = PersistData.persist(albums);
            return Response.created(URI.create("/" + albumId)).build();
        } catch (Exception e) {
            throw new WebApplicationException(e, Response.Status.INTERNAL_SERVER_ERROR);
        }
    }

    @GET
    @Path("{id}")
    @Produces("application/xml")
    public StreamingOutput retrieveAlbum(@PathParam("id") String albumId) {
        try {

            String albumDetails = PersistData.loadAlbums(albumId);
                        
            return new StreamingOutput() {
                public void write(OutputStream outputStream) {
                    PrintWriter out = new PrintWriter(outputStream);
                    out.println(albumDetails);
                    out.close();
                }
            };
        } catch (Exception e) {
            throw new WebApplicationException(e, Response.Status.INTERNAL_SERVER_ERROR);
        }
    }

    @PUT
    @Path("{id}")
    @Consumes("application/xml")
    public void updateAlbum(@PathParam("id") String albumId, InputStream input) {
        try {
            String albumDetails = PersistData.loadAlbums(albumId);
            if (albumDetails == null) {
                throw new WebApplicationException(Response.Status.NOT_FOUND);
            }
            Albums album = buildAlbum.parseAlbum(null, input);
            PersistData.persistupdate(album);
        } catch (Exception e) {
            throw new WebApplicationException(e, Response.Status.INTERNAL_SERVER_ERROR);
        }
    }

    @DELETE
    @Path("{id}")
    public void deleteAlbum(@PathParam("id") String albumId) {
        try {
            String albumDetails = PersistData.loadAlbums(albumId);
            if (albumDetails == null) {
                throw new WebApplicationException(Response.Status.NOT_FOUND);
            }
            PersistData.deleteData(albumId);
        } catch (Exception e) {
            throw new WebApplicationException(e, Response.Status.INTERNAL_SERVER_ERROR);
        }
    }
}
