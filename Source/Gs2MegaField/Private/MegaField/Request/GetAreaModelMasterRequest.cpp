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

#include "MegaField/Request/GetAreaModelMasterRequest.h"

namespace Gs2::MegaField::Request
{
    FGetAreaModelMasterRequest::FGetAreaModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>())
    {
    }

    FGetAreaModelMasterRequest::FGetAreaModelMasterRequest(
        const FGetAreaModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AreaModelNameValue(From.AreaModelNameValue)
    {
    }

    TSharedPtr<FGetAreaModelMasterRequest> FGetAreaModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetAreaModelMasterRequest> FGetAreaModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetAreaModelMasterRequest> FGetAreaModelMasterRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TOptional<FString> FGetAreaModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetAreaModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetAreaModelMasterRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TSharedPtr<FGetAreaModelMasterRequest> FGetAreaModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetAreaModelMasterRequest>()
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
            ->WithAreaModelName(Data->HasField("areaModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("areaModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetAreaModelMasterRequest::ToJson() const
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
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        return JsonRootObject;
    }
}