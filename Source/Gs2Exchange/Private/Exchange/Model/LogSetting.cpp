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

#include "Exchange/Model/LogSetting.h"

namespace Gs2::Exchange::Model
{
    FLogSetting::FLogSetting():
        LoggingNamespaceIdValue(TOptional<FString>())
    {
    }

    FLogSetting::FLogSetting(
        const FLogSetting& From
    ):
        LoggingNamespaceIdValue(From.LoggingNamespaceIdValue)
    {
    }

    TSharedPtr<FLogSetting> FLogSetting::WithLoggingNamespaceId(
        const TOptional<FString> LoggingNamespaceId
    )
    {
        this->LoggingNamespaceIdValue = LoggingNamespaceId;
        return SharedThis(this);
    }
    TOptional<FString> FLogSetting::GetLoggingNamespaceId() const
    {
        return LoggingNamespaceIdValue;
    }

    TSharedPtr<FLogSetting> FLogSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLogSetting>()
            ->WithLoggingNamespaceId(Data->HasField("loggingNamespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("loggingNamespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FLogSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (LoggingNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("loggingNamespaceId", LoggingNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FLogSetting::TypeName = "LogSetting";
}