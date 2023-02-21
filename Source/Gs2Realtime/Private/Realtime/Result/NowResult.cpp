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

#include "Realtime/Result/NowResult.h"

namespace Gs2::Realtime::Result
{
    FNowResult::FNowResult():
        TimestampValue(TOptional<int64>())
    {
    }

    FNowResult::FNowResult(
        const FNowResult& From
    ):
        TimestampValue(From.TimestampValue)
    {
    }

    TSharedPtr<FNowResult> FNowResult::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TOptional<int64> FNowResult::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FNowResult::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    TSharedPtr<FNowResult> FNowResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNowResult>()
            ->WithTimestamp(Data->HasField("timestamp") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("timestamp", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FNowResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        return JsonRootObject;
    }
}