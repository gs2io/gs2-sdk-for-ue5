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

#include "Datastore/Request/PrepareDownloadByUserIdAndDataObjectNameRequest.h"

namespace Gs2::Datastore::Request
{
    FPrepareDownloadByUserIdAndDataObjectNameRequest::FPrepareDownloadByUserIdAndDataObjectNameRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DataObjectNameValue(TOptional<FString>())
    {
    }

    FPrepareDownloadByUserIdAndDataObjectNameRequest::FPrepareDownloadByUserIdAndDataObjectNameRequest(
        const FPrepareDownloadByUserIdAndDataObjectNameRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        DataObjectNameValue(From.DataObjectNameValue)
    {
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::WithDataObjectName(
        const TOptional<FString> DataObjectName
    )
    {
        this->DataObjectNameValue = DataObjectName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameRequest::GetDataObjectName() const
    {
        return DataObjectNameValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameRequest> FPrepareDownloadByUserIdAndDataObjectNameRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareDownloadByUserIdAndDataObjectNameRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
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
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareDownloadByUserIdAndDataObjectNameRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (DataObjectNameValue.IsSet())
        {
            JsonRootObject->SetStringField("dataObjectName", DataObjectNameValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}