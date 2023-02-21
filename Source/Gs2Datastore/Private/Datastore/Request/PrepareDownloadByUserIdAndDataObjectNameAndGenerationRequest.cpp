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

#include "Datastore/Request/PrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest.h"

namespace Gs2::Datastore::Request
{
    FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DataObjectNameValue(TOptional<FString>()),
        GenerationValue(TOptional<FString>())
    {
    }

    FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest(
        const FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        DataObjectNameValue(From.DataObjectNameValue),
        GenerationValue(From.GenerationValue)
    {
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithDataObjectName(
        const TOptional<FString> DataObjectName
    )
    {
        this->DataObjectNameValue = DataObjectName;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithGeneration(
        const TOptional<FString> Generation
    )
    {
        this->GenerationValue = Generation;
        return SharedThis(this);
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetDataObjectName() const
    {
        return DataObjectNameValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetGeneration() const
    {
        return GenerationValue;
    }

    TOptional<FString> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest>()
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
            ->WithGeneration(Data->HasField("generation") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("generation", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest::ToJson() const
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
        if (GenerationValue.IsSet())
        {
            JsonRootObject->SetStringField("generation", GenerationValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}