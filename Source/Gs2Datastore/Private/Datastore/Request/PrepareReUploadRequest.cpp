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

#include "Datastore/Request/PrepareReUploadRequest.h"

namespace Gs2::Datastore::Request
{
    FPrepareReUploadRequest::FPrepareReUploadRequest():
        NamespaceNameValue(TOptional<FString>()),
        DataObjectNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ContentTypeValue(TOptional<FString>())
    {
    }

    FPrepareReUploadRequest::FPrepareReUploadRequest(
        const FPrepareReUploadRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        DataObjectNameValue(From.DataObjectNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ContentTypeValue(From.ContentTypeValue)
    {
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithDataObjectName(
        const TOptional<FString> DataObjectName
    )
    {
        this->DataObjectNameValue = DataObjectName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithContentType(
        const TOptional<FString> ContentType
    )
    {
        this->ContentTypeValue = ContentType;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareReUploadRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPrepareReUploadRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPrepareReUploadRequest::GetDataObjectName() const
    {
        return DataObjectNameValue;
    }

    TOptional<FString> FPrepareReUploadRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FPrepareReUploadRequest::GetContentType() const
    {
        return ContentTypeValue;
    }

    TOptional<FString> FPrepareReUploadRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPrepareReUploadRequest> FPrepareReUploadRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareReUploadRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDataObjectName(Data->HasField("dataObjectName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("dataObjectName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithContentType(Data->HasField("contentType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("contentType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareReUploadRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (DataObjectNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectName", DataObjectNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (ContentTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("contentType", ContentTypeValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}