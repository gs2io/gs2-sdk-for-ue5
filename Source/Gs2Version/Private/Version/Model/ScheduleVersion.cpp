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

#include "Version/Model/ScheduleVersion.h"

namespace Gs2::Version::Model
{
    FScheduleVersion::FScheduleVersion():
        CurrentVersionValue(nullptr),
        WarningVersionValue(nullptr),
        ErrorVersionValue(nullptr),
        ScheduleEventIdValue(TOptional<FString>())
    {
    }

    FScheduleVersion::FScheduleVersion(
        const FScheduleVersion& From
    ):
        CurrentVersionValue(From.CurrentVersionValue),
        WarningVersionValue(From.WarningVersionValue),
        ErrorVersionValue(From.ErrorVersionValue),
        ScheduleEventIdValue(From.ScheduleEventIdValue)
    {
    }

    TSharedPtr<FScheduleVersion> FScheduleVersion::WithCurrentVersion(
        const TSharedPtr<FVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }

    TSharedPtr<FScheduleVersion> FScheduleVersion::WithWarningVersion(
        const TSharedPtr<FVersion> WarningVersion
    )
    {
        this->WarningVersionValue = WarningVersion;
        return SharedThis(this);
    }

    TSharedPtr<FScheduleVersion> FScheduleVersion::WithErrorVersion(
        const TSharedPtr<FVersion> ErrorVersion
    )
    {
        this->ErrorVersionValue = ErrorVersion;
        return SharedThis(this);
    }

    TSharedPtr<FScheduleVersion> FScheduleVersion::WithScheduleEventId(
        const TOptional<FString> ScheduleEventId
    )
    {
        this->ScheduleEventIdValue = ScheduleEventId;
        return SharedThis(this);
    }
    TSharedPtr<FVersion> FScheduleVersion::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }
    TSharedPtr<FVersion> FScheduleVersion::GetWarningVersion() const
    {
        return WarningVersionValue;
    }
    TSharedPtr<FVersion> FScheduleVersion::GetErrorVersion() const
    {
        return ErrorVersionValue;
    }
    TOptional<FString> FScheduleVersion::GetScheduleEventId() const
    {
        return ScheduleEventIdValue;
    }

    TSharedPtr<FScheduleVersion> FScheduleVersion::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FScheduleVersion>()
            ->WithCurrentVersion(Data->HasField("currentVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("currentVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("currentVersion"));
                 }() : nullptr)
            ->WithWarningVersion(Data->HasField("warningVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("warningVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("warningVersion"));
                 }() : nullptr)
            ->WithErrorVersion(Data->HasField("errorVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("errorVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("errorVersion"));
                 }() : nullptr)
            ->WithScheduleEventId(Data->HasField("scheduleEventId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("scheduleEventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FScheduleVersion::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CurrentVersionValue != nullptr && CurrentVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("currentVersion", CurrentVersionValue->ToJson());
        }
        if (WarningVersionValue != nullptr && WarningVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("warningVersion", WarningVersionValue->ToJson());
        }
        if (ErrorVersionValue != nullptr && ErrorVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorVersion", ErrorVersionValue->ToJson());
        }
        if (ScheduleEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleEventId", ScheduleEventIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FScheduleVersion::TypeName = "ScheduleVersion";
}