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

    bool FGs2Error::IsChildOf( const FGs2ErrorType& BaseClass ) const
    {
        const auto SuperTypeString = ":" + this->SuperType() + ":";
        const auto BaseClassString = ":" + BaseClass + ":";
        return SuperTypeString.Contains(BaseClassString);
    }
    
    TSharedPtr<FGs2Error> FGs2Error::FromResponse(int32 ResponseCode, FString Response)
    {
        UE_LOG(Gs2Log, Warning, TEXT("[%d] %s"), ResponseCode, ToCStr(Response));

        if (Response.IsEmpty())
        {
            return FromJson(ResponseCode, TArray<TSharedPtr<FJsonValue>>(), nullptr);
        }

        const auto ParseFailed = []
        {
            auto Details = MakeShared<TArray<TSharedPtr<FGs2ErrorDetail>>>();
            Details->Add(MakeShared<FGs2ErrorDetail>(
                TEXT("client"),
                TEXT("core.network.result.error.parse.failed"),
                TEXT("")));
            return MakeShared<FUnknownError>(Details);
        };

        TSharedPtr<FJsonValue> OuterValue;
        if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response);
            !FJsonSerializer::Deserialize(JsonReader, OuterValue) ||
            !OuterValue.IsValid() ||
            OuterValue->Type != EJson::Object)
        {
            return ParseFailed();
        }
        const auto JsonRootObject = OuterValue->AsObject();
        if (!JsonRootObject.IsValid() ||
            !JsonRootObject->HasField(ANSI_TO_TCHAR("message")) ||
            !JsonRootObject->HasTypedField<EJson::String>(ANSI_TO_TCHAR("message")) ||
            (JsonRootObject->HasField(ANSI_TO_TCHAR("metadata")) &&
                !JsonRootObject->HasTypedField<EJson::Object>(ANSI_TO_TCHAR("metadata")) &&
                !JsonRootObject->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("metadata"))))
        {
            return ParseFailed();
        }

        FResultMetadataPtr ParsedMetadata;
        if (JsonRootObject->HasTypedField<EJson::Object>(ANSI_TO_TCHAR("metadata")))
        {
            ParsedMetadata = FResultMetadata::FromJson(JsonRootObject->GetObjectField(ANSI_TO_TCHAR("metadata")));
        }
        const auto Message = JsonRootObject->GetStringField(ANSI_TO_TCHAR("message"));
        TSharedPtr<FJsonValue> MessageValue;
        if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Message);
            FJsonSerializer::Deserialize(JsonReader, MessageValue) &&
            MessageValue.IsValid() &&
            MessageValue->Type == EJson::Array)
        {
            return FromJson(ResponseCode, MessageValue->AsArray(), ParsedMetadata);
        }
        return FromJson(ResponseCode, TArray<TSharedPtr<FJsonValue>>(), ParsedMetadata);
    }

    TSharedPtr<FGs2ErrorDetail> FGs2ErrorDetail::FromJson(TSharedPtr<FJsonValue> Object)
    {
        if (!Object.IsValid() || Object->Type != EJson::Object || !Object->AsObject().IsValid())
        {
            return nullptr;
        }
        const auto JsonObject = Object->AsObject();
        const auto IsStringOrNull = [&JsonObject](const TCHAR* Name)
        {
            return !JsonObject->HasField(Name) ||
                JsonObject->HasTypedField<EJson::String>(Name) ||
                JsonObject->HasTypedField<EJson::Null>(Name);
        };
        if (!IsStringOrNull(ANSI_TO_TCHAR("component")) ||
            !IsStringOrNull(ANSI_TO_TCHAR("message")) ||
            !IsStringOrNull(ANSI_TO_TCHAR("code")))
        {
            return nullptr;
        }
        const auto GetStringOrEmpty = [&JsonObject](const TCHAR* Name)
        {
            return JsonObject->HasTypedField<EJson::String>(Name)
                ? JsonObject->GetStringField(Name)
                : FString();
        };
        return MakeShared<FGs2ErrorDetail>(
            GetStringOrEmpty(ANSI_TO_TCHAR("component")),
            GetStringOrEmpty(ANSI_TO_TCHAR("message")),
            GetStringOrEmpty(ANSI_TO_TCHAR("code"))
        );
    }

    FString FGs2ErrorDetail::String() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        JsonRootObject->SetStringField(TEXT("component"), ComponentValue);
        JsonRootObject->SetStringField(TEXT("message"), MessageValue);
        JsonRootObject->SetStringField(TEXT("code"), CodeValue);
        FString Body;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
        FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
        return Body;
    }

    FGs2Error::FGs2Error(
        const TSharedPtr<TArray<TSharedPtr<FGs2ErrorDetail>>> Details,
        const FResultMetadataPtr InMetadata
    ): Details(Details), Metadata(InMetadata)
    {
    }

    FGs2Error::FGs2Error(
        const FGs2Error& From
    ): Details(From.Details), Metadata(From.Metadata)
    {
    }

    TSharedPtr<FGs2Error> FGs2Error::FromJson(int32 StatusCode, TArray<TSharedPtr<FJsonValue>> Objects, const FResultMetadataPtr InMetadata)
    {
        auto Errors = MakeShared<TArray<TSharedPtr<FGs2ErrorDetail>>>();
        bool bInvalidDetail = false;
        for (auto Object : Objects)
        {
            const auto Error = FGs2ErrorDetail::FromJson(Object);
            if (!Error.IsValid())
            {
                bInvalidDetail = true;
                break;
            }
            Errors->Add(MakeShared<FGs2ErrorDetail>(
                Error->Component(),
                Error->Message(),
                Error->Code()
            ));
        }
        if (bInvalidDetail)
        {
            Errors->Reset();
        }
        TSharedPtr<FGs2Error> Error;
        switch (StatusCode)
        {
        case 0:
            Error = MakeShared<FNoInternetConnectionError>(Errors);
            break;
        case 400: 
            Error = MakeShared<FBadRequestError>(Errors);
            break;
        case 401: 
            Error = MakeShared<FUnauthorizedError>(Errors);
            break;
        case 402: 
            Error = MakeShared<FQuotaLimitExceedError>(Errors);
            break;
        case 404: 
            Error = MakeShared<FNotFoundError>(Errors);
            break;
        case 409: 
            Error = MakeShared<FConflictError>(Errors);
            break;
        case 500: 
            Error = MakeShared<FInternalServerError>(Errors);
            break;
        case 502: 
            Error = MakeShared<FBadGatewayError>(Errors);
            break;
        case 503: 
            Error = MakeShared<FServiceUnavailableError>(Errors);
            break;
        case 504: 
            Error = MakeShared<FRequestTimeoutError>(Errors);
            break;
        default: 
            Error = MakeShared<FUnknownError>(Errors);
            break;
        }
        Error->SetMetadata(InMetadata);
        return Error;
    }

    FString FGs2Error::String() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (Details.IsValid())
        {
            JsonRootObject->SetArrayField(TEXT("errors"), [&]
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
