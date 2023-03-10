/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#include "Core/Model/Gs2Error.h"
#include "Core/Gs2Constant.h"

namespace Gs2::Core::Model
{
    FGs2ErrorDetail::FGs2ErrorDetail(
        const FGs2ErrorComponent ComponentValue,
        const FGs2ErrorMessage MessageValue,
        const FGs2ErrorCode CodeValue
    ):
        ComponentValue(ComponentValue),
        MessageValue(MessageValue),
        CodeValue(CodeValue)
    {
            
    }

    FGs2ErrorDetail::FGs2ErrorDetail(
        const FGs2ErrorDetail& From
    ):
        ComponentValue(From.ComponentValue),
        MessageValue(From.MessageValue),
        CodeValue(From.CodeValue)
    {
    }

    FGs2ErrorComponent FGs2ErrorDetail::Component() const
    {
        return ComponentValue;
    }

    FGs2ErrorMessage FGs2ErrorDetail::Message() const
    {
        return MessageValue;
    }

    FGs2ErrorCode FGs2ErrorDetail::Code() const
    {
        return CodeValue;
    }

    FGs2ErrorComponent FGs2ErrorDetail::GetComponent() const
    {
        return ComponentValue;
    }

    FGs2ErrorMessage FGs2ErrorDetail::GetMessage() const
    {
        return MessageValue;
    }

    FGs2ErrorCode FGs2ErrorDetail::GetCode() const
    {
        return CodeValue;
    }

    TSharedPtr<FGs2Error> FGs2Error::FromResponse(int32 ResponseCode, FString Response)
    {
        UE_LOG(Gs2Log, Warning, TEXT("[%d] %s"), ResponseCode, ToCStr(Response));
        
        TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
            FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
        {
            const auto Message = JsonRootObject->GetStringField("message");
            TSharedPtr<FJsonValue> JsonRootObject2;
            if (JsonReader = TJsonReaderFactory<>::Create(Message);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject2))
            {
                return FromJson(ResponseCode, JsonRootObject2->AsArray());
            }
        }
        auto Details = MakeShared<TArray<TSharedPtr<FGs2ErrorDetail>>>();
        return MakeShared<FUnknownError>(Details);
    }

    TSharedPtr<FGs2ErrorDetail> FGs2ErrorDetail::FromJson(TSharedPtr<FJsonValue> Object)
    {
        return MakeShared<FGs2ErrorDetail>(
            Object->AsObject()->GetStringField("component"),
            Object->AsObject()->GetStringField("message"),
            Object->AsObject()->GetStringField("code")
        );
    }

    FString FGs2ErrorDetail::String() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        JsonRootObject->SetStringField("component", ComponentValue);
        JsonRootObject->SetStringField("message", MessageValue);
        JsonRootObject->SetStringField("code", CodeValue);
        FString Body;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
        FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
        return Body;
    }

    FGs2Error::FGs2Error(
        const TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details
    ): Details(Details)
    {
    }

    FGs2Error::FGs2Error(
        const FGs2Error& From
    ): Details(From.Details)
    {
    }

    TSharedPtr<FGs2Error> FGs2Error::FromJson(int32 StatusCode, TArray<TSharedPtr<FJsonValue>> Objects)
    {
        auto Errors = MakeShared<TArray<TSharedPtr<FGs2ErrorDetail>>>();
        for (auto Object : Objects)
        {
            const auto Error = FGs2ErrorDetail::FromJson(Object);
            Errors->Add(MakeShared<FGs2ErrorDetail>(
                Error->Component(),
                Error->Message(),
                Error->Code()
            ));
        }
        switch (StatusCode)
        {
        case 400: 
            return MakeShared<FBadRequestError>(Errors);
        case 401: 
            return MakeShared<FUnauthorizedError>(Errors);
        case 402: 
            return MakeShared<FQuotaLimitExceedError>(Errors);
        case 404: 
            return MakeShared<FNotFoundError>(Errors);
        case 409: 
            return MakeShared<FConflictError>(Errors);
        case 500: 
            return MakeShared<FInternalServerError>(Errors);
        case 502: 
            return MakeShared<FBadGatewayError>(Errors);
        case 503: 
            return MakeShared<FServiceUnavailableError>(Errors);
        case 504: 
            return MakeShared<FRequestTimeoutError>(Errors);
        default: 
            return MakeShared<FUnknownError>(Errors);
        }
    }

    FString FGs2Error::String() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (Details.IsValid())
        {
            JsonRootObject->SetArrayField("errors", [&]
            {
                TArray<TSharedPtr<FJsonValue>> Arr;
                for (auto v : *Details)
                {
                    Arr.Add(MakeShared<FJsonValueString>(v->String()));
                }
                return Arr;
            }());
        }
        FString Body;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
        FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
        return Body;
    }
}
