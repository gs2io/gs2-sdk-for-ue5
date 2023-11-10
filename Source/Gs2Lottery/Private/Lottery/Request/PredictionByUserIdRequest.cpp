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

#include "Lottery/Request/PredictionByUserIdRequest.h"

namespace Gs2::Lottery::Request
{
    FPredictionByUserIdRequest::FPredictionByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        LotteryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RandomSeedValue(TOptional<int64>()),
        CountValue(TOptional<int32>())
    {
    }

    FPredictionByUserIdRequest::FPredictionByUserIdRequest(
        const FPredictionByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        LotteryNameValue(From.LotteryNameValue),
        UserIdValue(From.UserIdValue),
        RandomSeedValue(From.RandomSeedValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithLotteryName(
        const TOptional<FString> LotteryName
    )
    {
        this->LotteryNameValue = LotteryName;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithRandomSeed(
        const TOptional<int64> RandomSeed
    )
    {
        this->RandomSeedValue = RandomSeed;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FPredictionByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FPredictionByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FPredictionByUserIdRequest::GetLotteryName() const
    {
        return LotteryNameValue;
    }

    TOptional<FString> FPredictionByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int64> FPredictionByUserIdRequest::GetRandomSeed() const
    {
        return RandomSeedValue;
    }

    FString FPredictionByUserIdRequest::GetRandomSeedString() const
    {
        if (!RandomSeedValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue());
    }

    TOptional<int32> FPredictionByUserIdRequest::GetCount() const
    {
        return CountValue;
    }

    FString FPredictionByUserIdRequest::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TOptional<FString> FPredictionByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FPredictionByUserIdRequest> FPredictionByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FPredictionByUserIdRequest>()
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
            ->WithLotteryName(Data->HasField("lotteryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("lotteryName", v))
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
            ->WithRandomSeed(Data->HasField("randomSeed") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("randomSeed", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithCount(Data->HasField("count") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("count", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FPredictionByUserIdRequest::ToJson() const
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
        if (LotteryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("lotteryName", LotteryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (RandomSeedValue.IsSet())
        {
            JsonRootObject->SetStringField("randomSeed", FString::Printf(TEXT("%lld"), RandomSeedValue.GetValue()));
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField("count", CountValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}