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

#include "MegaField/Request/NearUserIdsRequest.h"

namespace Gs2::MegaField::Request
{
    FNearUserIdsRequest::FNearUserIdsRequest():
        NamespaceNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        PointValue(nullptr),
        RValue(TOptional<float>()),
        LimitValue(TOptional<int32>())
    {
    }

    FNearUserIdsRequest::FNearUserIdsRequest(
        const FNearUserIdsRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        AccessTokenValue(From.AccessTokenValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        PointValue(From.PointValue),
        RValue(From.RValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithPoint(
        const TSharedPtr<Model::FPosition> Point
    )
    {
        this->PointValue = Point;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FNearUserIdsRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FNearUserIdsRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FNearUserIdsRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FNearUserIdsRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FNearUserIdsRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<Model::FPosition> FNearUserIdsRequest::GetPoint() const
    {
        if (!PointValue.IsValid())
        {
            return nullptr;
        }
        return PointValue;
    }

    TOptional<float> FNearUserIdsRequest::GetR() const
    {
        return RValue;
    }

    FString FNearUserIdsRequest::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }

    TOptional<int32> FNearUserIdsRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FNearUserIdsRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TOptional<FString> FNearUserIdsRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FNearUserIdsRequest> FNearUserIdsRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNearUserIdsRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAreaModelName(Data->HasField("areaModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("areaModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLayerModelName(Data->HasField("layerModelName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("layerModelName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithPoint(Data->HasField("point") ? [Data]() -> Model::FPositionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("point"))
                  {
                      return nullptr;
                  }
                  return Model::FPosition::FromJson(Data->GetObjectField("point"));
             }() : nullptr)
            ->WithR(Data->HasField("r") ? [Data]() -> TOptional<float>
              {
                  float v;
                    if (Data->TryGetNumberField("r", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<float>();
              }() : TOptional<float>())
            ->WithLimit(Data->HasField("limit") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("limit", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FNearUserIdsRequest::ToJson() const
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
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        if (PointValue != nullptr && PointValue.IsValid())
        {
            JsonRootObject->SetObjectField("point", PointValue->ToJson());
        }
        if (RValue.IsSet())
        {
            JsonRootObject->SetNumberField("r", RValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}