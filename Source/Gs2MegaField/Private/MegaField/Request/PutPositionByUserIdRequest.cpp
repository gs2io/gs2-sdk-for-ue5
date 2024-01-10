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

#include "MegaField/Request/PutPositionByUserIdRequest.h"

namespace Gs2::MegaField::Request
{
    FPutPositionByUserIdRequest::FPutPositionByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AreaModelNameValue(TOptional<FString>()),
        LayerModelNameValue(TOptional<FString>()),
        PositionValue(nullptr),
        VectorValue(nullptr),
        RValue(TOptional<float>())
    {
    }

    FPutPositionByUserIdRequest::FPutPositionByUserIdRequest(
        const FPutPositionByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        AreaModelNameValue(From.AreaModelNameValue),
        LayerModelNameValue(From.LayerModelNameValue),
        PositionValue(From.PositionValue),
        VectorValue(From.VectorValue),
        RValue(From.RValue)
    {
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithAreaModelName(
        const TOptional<FString> AreaModelName
    )
    {
        this->AreaModelNameValue = AreaModelName;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithLayerModelName(
        const TOptional<FString> LayerModelName
    )
    {
        this->LayerModelNameValue = LayerModelName;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithPosition(
        const TSharedPtr<Model::FPosition> Position
    )
    {
        this->PositionValue = Position;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithVector(
        const TSharedPtr<Model::FVector> Vector
    )
    {
        this->VectorValue = Vector;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithR(
        const TOptional<float> R
    )
    {
        this->RValue = R;
        return SharedThis(this);
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetAreaModelName() const
    {
        return AreaModelNameValue;
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetLayerModelName() const
    {
        return LayerModelNameValue;
    }

    TSharedPtr<Model::FPosition> FPutPositionByUserIdRequest::GetPosition() const
    {
        if (!PositionValue.IsValid())
        {
            return nullptr;
        }
        return PositionValue;
    }

    TSharedPtr<Model::FVector> FPutPositionByUserIdRequest::GetVector() const
    {
        if (!VectorValue.IsValid())
        {
            return nullptr;
        }
        return VectorValue;
    }

    TOptional<float> FPutPositionByUserIdRequest::GetR() const
    {
        return RValue;
    }

    FString FPutPositionByUserIdRequest::GetRString() const
    {
        if (!RValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RValue.GetValue());
    }

    TOptional<FString> FPutPositionByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPutPositionByUserIdRequest> FPutPositionByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPutPositionByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
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
          ->WithPosition(Data->HasField("position") ? [Data]() -> Model::FPositionPtr
              {
                  if (Data->HasTypedField<EJson::Null>("position"))
                  {
                      return nullptr;
                  }
                  return Model::FPosition::FromJson(Data->GetObjectField("position"));
              }() : nullptr)
          ->WithVector(Data->HasField("vector") ? [Data]() -> Model::FVectorPtr
              {
                  if (Data->HasTypedField<EJson::Null>("vector"))
                  {
                      return nullptr;
                  }
                  return Model::FVector::FromJson(Data->GetObjectField("vector"));
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
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPutPositionByUserIdRequest::ToJson() const
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
        if (AreaModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("areaModelName", AreaModelNameValue.GetValue());
        }
        if (LayerModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("layerModelName", LayerModelNameValue.GetValue());
        }
        if (PositionValue != nullptr && PositionValue.IsValid())
        {
            JsonRootObject->SetObjectField("position", PositionValue->ToJson());
        }
        if (VectorValue != nullptr && VectorValue.IsValid())
        {
            JsonRootObject->SetObjectField("vector", VectorValue->ToJson());
        }
        if (RValue.IsSet())
        {
            JsonRootObject->SetNumberField("r", RValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}