<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:template match="/">
        <html>
            <head>
                <title>BSA</title>
                <style>
                    td 
                    {
                        padding-right: 20px;
                    }
                    h1
                    {
                        text-transform: capitalize
                    }
                </style>
            </head>
            <body>
                <ul>
                    <xsl:for-each select="bsa/council"> 
                        <li>
                            <h1><xsl:value-of select="@name" /></h1>
                            <ul>
                                <xsl:for-each select="troop"> 
                                    <li>
                                        <h2><xsl:value-of select="@number" /> - <xsl:value-of select="@name" /></h2>
                                        <ul>
                                            <xsl:for-each select="scout"> 
                                                <li>
                                                    <table>
                                                        <tr>
                                                            <td><xsl:value-of select="firstname" /></td>
                                                            <td><xsl:value-of select="lastname" /></td>
                                                            <td>
                                                                <xsl:value-of select="address/street" />
                                                                <xsl:value-of select="address/city" />,
                                                                <xsl:value-of select="address/state" />
                                                            </td>
                                                            <td><xsl:value-of select="phone" /></td>
                                                            <td>
                                                                |<xsl:for-each select="rank">
                                                                    <xsl:value-of select="current()" />|
                                                                </xsl:for-each>
                                                            </td>
                                                            <td>
                                                                |<xsl:for-each select="meritbadge">
                                                                    <xsl:value-of select="current()" />|
                                                                </xsl:for-each>
                                                            </td>
                                                        </tr>
                                                    </table>
                                                </li>
                                            </xsl:for-each>
                                        </ul>
                                    </li>
                                </xsl:for-each>
                            </ul>
                        </li>
                    </xsl:for-each>
                </ul>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>