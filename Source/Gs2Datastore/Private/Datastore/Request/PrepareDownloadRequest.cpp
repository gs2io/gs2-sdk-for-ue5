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

#include "Datastore/Request/PrepareDownloadRequest.h"

namespace Gs2::Datastore::Request
{
    FPrepareDownloadRequest::FPrepareDownloadRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        DataObjectIdValue(TOptional<FString>())
    {
    }

    FPrepareDownloadRequest::FPrepareDownloadRequest(
        const FPrepareDownloadRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        DataObjectIdValue(From.DataObjectIdValue)
    {
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::WithDataObjectId(
        const TOptional<FString> DataObjectId
    )
    {
        this->DataObjectIdValue = DataObjectId;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareDownloadRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPrepareDownloadRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPrepareDownloadRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FPrepareDownloadRequest::GetDataObjectId() const
    {
        return DataObjectIdValue;
    }

    TOptional<FString> FPrepareDownloadRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPrepareDownloadRequest> FPrepareDownloadRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareDownloadRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDataObjectId(Data->HasField("dataObjectId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("dataObjectId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareDownloadRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (DataObjectIdValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectId", DataObjectIdValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}