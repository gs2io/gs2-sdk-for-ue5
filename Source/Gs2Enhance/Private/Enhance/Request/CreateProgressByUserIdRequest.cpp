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

#include "Enhance/Request/CreateProgressByUserIdRequest.h"

namespace Gs2::Enhance::Request
{
    FCreateProgressByUserIdRequest::FCreateProgressByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        TargetItemSetIdValue(TOptional<FString>()),
        MaterialsValue(nullptr),
        ForceValue(TOptional<bool>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FCreateProgressByUserIdRequest::FCreateProgressByUserIdRequest(
        const FCreateProgressByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        RateNameValue(From.RateNameValue),
        TargetItemSetIdValue(From.TargetItemSetIdValue),
        MaterialsValue(From.MaterialsValue),
        ForceValue(From.ForceValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithTargetItemSetId(
        const TOptional<FString> TargetItemSetId
    )
    {
        this->TargetItemSetIdValue = TargetItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithMaterials(
        const TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> Materials
    )
    {
        this->MaterialsValue = Materials;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithForce(
        const TOptional<bool> Force
    )
    {
        this->ForceValue = Force;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetTargetItemSetId() const
    {
        return TargetItemSetIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FMaterial>>> FCreateProgressByUserIdRequest::GetMaterials() const
    {
        if (!MaterialsValue.IsValid())
        {
            return nullptr;
        }
        return MaterialsValue;
    }

    TOptional<bool> FCreateProgressByUserIdRequest::GetForce() const
    {
        return ForceValue;
    }

    FString FCreateProgressByUserIdRequest::GetForceString() const
    {
        if (!ForceValue.IsSet())
        {
            return FString("null");
        }
        return FString(ForceValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TOptional<FString> FCreateProgressByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCreateProgressByUserIdRequest> FCreateProgressByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateProgressByUserIdRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRateName(Data->HasField(ANSI_TO_TCHAR("rateName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rateName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithTargetItemSetId(Data->HasField(ANSI_TO_TCHAR("targetItemSetId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("targetItemSetId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithMaterials(Data->HasField(ANSI_TO_TCHAR("materials")) ? [Data]() -> TSharedPtr<TArray<Model::FMaterialPtr>>
              {
                  auto v = MakeShared<TArray<Model::FMaterialPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("materials")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("materials")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("materials")))
                      {
                          v->Add(Model::FMaterial::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FMaterialPtr>>())
            ->WithForce(Data->HasField(ANSI_TO_TCHAR("force")) ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("force"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithTimeOffsetToken(Data->HasField(ANSI_TO_TCHAR("timeOffsetToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("timeOffsetToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField(ANSI_TO_TCHAR("duplicationAvoider")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("duplicationAvoider"))) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateProgressByUserIdRequest::ToJson() const
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
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (TargetItemSetIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetItemSetId", TargetItemSetIdValue.GetValue());
        }
        if (MaterialsValue != nullptr && MaterialsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MaterialsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("materials", v);
        }
        if (ForceValue.IsSet())
        {
            JsonRootObject->SetBoolField("force", ForceValue.GetValue());
        }
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}