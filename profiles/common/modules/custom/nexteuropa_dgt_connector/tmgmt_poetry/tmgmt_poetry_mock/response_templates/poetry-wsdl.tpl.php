<?php

/**
 * @file
 * Template file for the POETRY mock WSDL.
 *
 * Available custom variables:
 * - $uri: uri of WSDL.
 */
?>
<definitions name="TMGMTPoetryTestSoapServer" targetNamespace="<?php print $uri; ?>" xmlns:tns="<?php print $uri; ?>/tmgmt_poetry_mock/soap_server" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:soap="http://schemas.xmlsoap.org/wsdl/soap/" xmlns:soapenc="http://schemas.xmlsoap.org/soap/encoding/" xmlns="http://schemas.xmlsoap.org/wsdl/" xmlns:ns="<?php print $uri; ?>/types">
  <types>
    <xsd:schema targetNamespace="<?php print $uri; ?>/types" xmlns="<?php print $uri; ?>/types"/>
  </types>
  <message name="requestServiceRequest">
    <part name="user" type="xsd:string"/>
    <part name="password" type="xsd:string"/>
    <part name="msg" type="xsd:string"/>
  </message>
  <message name="requestServiceResponse">
    <part name="requestServiceReturn" type="xsd:string">
    </part>
  </message>
  <portType name="TMGMTPoetryTestSoapServerPortType">
    <operation name="requestService">
      <input message="tns:requestServiceRequest"/>
      <output message="tns:requestServiceResponse"/>
    </operation>
  </portType>
  <binding name="TMGMTPoetryTestSoapServerBinding" type="tns:TMGMTPoetryTestSoapServerPortType">
    <soap:binding style="rpc" transport="http://schemas.xmlsoap.org/soap/http"/>
    <operation name="requestService">
      <soap:operation soapAction="<?php print $uri; ?>/#requestService"/>
      <input>
      <soap:body use="literal" namespace="<?php print $uri; ?>"/>
      </input>
      <output>
        <soap:body use="literal" namespace="<?php print $uri; ?>"/>
      </output>
    </operation>
  </binding>
  <service name="TMGMTPoetryTestSoapServerService">
    <port name="TMGMTPoetryTestSoapServerPort" binding="tns:TMGMTPoetryTestSoapServerBinding">
      <soap:address location="<?php print $uri; ?>"/>
    </port>
  </service>
</definitions>
