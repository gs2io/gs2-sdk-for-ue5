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

#include "MegaField/Request/GetLayerModelRequest.h"

namespace Gs2::MegaField::Request
{
    FGetLayerModelRequest::FGetLayerModelRequest():
        NamespaceNameValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>())
    {
    }

    FGetLayerModelRequest::FGetLayerModelRequest(
        const FGetLayerModelRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue)
    {
    }

    TSharedPtr<FGetLayerModelRequest> FGetLayerModelRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetLayerModelRequest> FGetLayerModelRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetLayerModelRequest> FGetLayerModelRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FGetLayerModelRequest> FGetLayerModelRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TOptional<FString> FGetLayerModelRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetLayerModelRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetLayerModelRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FGetLayerModelRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<FGetLayerModelRequest> FGetLayerModelRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetLayerModelRequest>()
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
              }() : TOptional<FString>())
            ->WithLayerModelName(Data->HasField("layerModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("layerModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetLayerModelRequest::ToJson() const
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
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        return JsonRootObject;
    }
}