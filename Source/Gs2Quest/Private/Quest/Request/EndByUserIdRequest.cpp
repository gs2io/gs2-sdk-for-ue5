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

#include "Quest/Request/EndByUserIdRequest.h"

namespace Gs2::Quest::Request
{
    FEndByUserIdRequest::FEndByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RewardsValue(nullptr),
        IsCompleteValue(TOptional<bool>()),
        ConfigValue(nullptr)
    {
    }

    FEndByUserIdRequest::FEndByUserIdRequest(
        const FEndByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        RewardsValue(From.RewardsValue),
        IsCompleteValue(From.IsCompleteValue),
        ConfigValue(From.ConfigValue)
    {
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithRewards(
        const TSharedPtr<TArray<TSharedPtr<Model::FReward>>> Rewards
    )
    {
        this->RewardsValue = Rewards;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithIsComplete(
        const TOptional<bool> IsComplete
    )
    {
        this->IsCompleteValue = IsComplete;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithConfig(
        const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config
    )
    {
        this->ConfigValue = Config;
        return SharedThis(this);
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FEndByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FEndByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FEndByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FReward>>> FEndByUserIdRequest::GetRewards() const
    {
        if (!RewardsValue.IsValid())
        {
            return nullptr;
        }
        return RewardsValue;
    }

    TOptional<bool> FEndByUserIdRequest::GetIsComplete() const
    {
        return IsCompleteValue;
    }

    FString FEndByUserIdRequest::GetIsCompleteString() const
    {
        if (!IsCompleteValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsCompleteValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> FEndByUserIdRequest::GetConfig() const
    {
        if (!ConfigValue.IsValid())
        {
            return nullptr;
        }
        return ConfigValue;
    }

    TOptional<FString> FEndByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FEndByUserIdRequest> FEndByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEndByUserIdRequest>()
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
          ->WithRewards(Data->HasField("rewards") ? [Data]() -> TSharedPtr<TArray<Model::FRewardPtr>>
              {
                  auto v = MakeShared<TArray<Model::FRewardPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("rewards") && Data->HasTypedField<EJson::Array>("rewards"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("rewards"))
                      {
                          v->Add(Model::FReward::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FRewardPtr>>())
            ->WithIsComplete(Data->HasField("isComplete") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("isComplete", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithConfig(Data->HasField("config") ? [Data]() -> TSharedPtr<TArray<Model::FConfigPtr>>
              {
                  auto v = MakeShared<TArray<Model::FConfigPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("config") && Data->HasTypedField<EJson::Array>("config"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("config"))
                      {
                          v->Add(Model::FConfig::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FConfigPtr>>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FEndByUserIdRequest::ToJson() const
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
        if (RewardsValue != nullptr && RewardsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RewardsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("rewards", v);
        }
        if (IsCompleteValue.IsSet())
        {
            JsonRootObject->SetBoolField("isComplete", IsCompleteValue.GetValue());
        }
        if (ConfigValue != nullptr && ConfigValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ConfigValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("config", v);
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}