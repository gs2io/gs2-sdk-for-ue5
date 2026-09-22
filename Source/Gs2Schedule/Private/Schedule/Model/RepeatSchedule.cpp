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
 *
 * deny overwrite: RepeatSchedule はモデルキャッシュを持たない seed だが、Model/Cache/RepeatSchedule.h（手書き）の
 * FRepeatScheduleCache の実装をこのファイルに手で足している。再生成すると消えてリンクで落ちる
 */

#include "Schedule/Model/RepeatSchedule.h"

namespace Gs2::Schedule::Model
{
    FRepeatSchedule::FRepeatSchedule():
        RepeatCountValue(TOptional<int32>()),
        CurrentRepeatStartAtValue(TOptional<int64>()),
        CurrentRepeatEndAtValue(TOptional<int64>()),
        LastRepeatEndAtValue(TOptional<int64>()),
        NextRepeatStartAtValue(TOptional<int64>())
    {
    }

    FRepeatSchedule::FRepeatSchedule(
        const FRepeatSchedule& From
    ):
        RepeatCountValue(From.RepeatCountValue),
        CurrentRepeatStartAtValue(From.CurrentRepeatStartAtValue),
        CurrentRepeatEndAtValue(From.CurrentRepeatEndAtValue),
        LastRepeatEndAtValue(From.LastRepeatEndAtValue),
        NextRepeatStartAtValue(From.NextRepeatStartAtValue)
    {
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithRepeatCount(
        const TOptional<int32> RepeatCount
    )
    {
        this->RepeatCountValue = RepeatCount;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithCurrentRepeatStartAt(
        const TOptional<int64> CurrentRepeatStartAt
    )
    {
        this->CurrentRepeatStartAtValue = CurrentRepeatStartAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithCurrentRepeatEndAt(
        const TOptional<int64> CurrentRepeatEndAt
    )
    {
        this->CurrentRepeatEndAtValue = CurrentRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithLastRepeatEndAt(
        const TOptional<int64> LastRepeatEndAt
    )
    {
        this->LastRepeatEndAtValue = LastRepeatEndAt;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::WithNextRepeatStartAt(
        const TOptional<int64> NextRepeatStartAt
    )
    {
        this->NextRepeatStartAtValue = NextRepeatStartAt;
        return SharedThis(this);
    }
    TOptional<int32> FRepeatSchedule::GetRepeatCount() const
    {
        return RepeatCountValue;
    }

    FString FRepeatSchedule::GetRepeatCountString() const
    {
        if (!RepeatCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatCountValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetCurrentRepeatStartAt() const
    {
        return CurrentRepeatStartAtValue;
    }

    FString FRepeatSchedule::GetCurrentRepeatStartAtString() const
    {
        if (!CurrentRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatStartAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetCurrentRepeatEndAt() const
    {
        return CurrentRepeatEndAtValue;
    }

    FString FRepeatSchedule::GetCurrentRepeatEndAtString() const
    {
        if (!CurrentRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CurrentRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetLastRepeatEndAt() const
    {
        return LastRepeatEndAtValue;
    }

    FString FRepeatSchedule::GetLastRepeatEndAtString() const
    {
        if (!LastRepeatEndAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LastRepeatEndAtValue.GetValue());
    }
    TOptional<int64> FRepeatSchedule::GetNextRepeatStartAt() const
    {
        return NextRepeatStartAtValue;
    }

    FString FRepeatSchedule::GetNextRepeatStartAtString() const
    {
        if (!NextRepeatStartAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), NextRepeatStartAtValue.GetValue());
    }

    TSharedPtr<FRepeatSchedule> FRepeatSchedule::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRepeatSchedule>()
            ->WithRepeatCount(Data->HasField(ANSI_TO_TCHAR("repeatCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("repeatCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithCurrentRepeatStartAt(Data->HasField(ANSI_TO_TCHAR("currentRepeatStartAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentRepeatStartAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCurrentRepeatEndAt(Data->HasField(ANSI_TO_TCHAR("currentRepeatEndAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentRepeatEndAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithLastRepeatEndAt(Data->HasField(ANSI_TO_TCHAR("lastRepeatEndAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("lastRepeatEndAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithNextRepeatStartAt(Data->HasField(ANSI_TO_TCHAR("nextRepeatStartAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("nextRepeatStartAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRepeatSchedule::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RepeatCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("repeatCount"), RepeatCountValue.GetValue());
        }
        if (CurrentRepeatStartAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("currentRepeatStartAt"), FString::Printf(TEXT("%lld"), CurrentRepeatStartAtValue.GetValue()));
        }
        if (CurrentRepeatEndAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("currentRepeatEndAt"), FString::Printf(TEXT("%lld"), CurrentRepeatEndAtValue.GetValue()));
        }
        if (LastRepeatEndAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("lastRepeatEndAt"), FString::Printf(TEXT("%lld"), LastRepeatEndAtValue.GetValue()));
        }
        if (NextRepeatStartAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("nextRepeatStartAt"), FString::Printf(TEXT("%lld"), NextRepeatStartAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRepeatSchedule::TypeName = "RepeatSchedule";
}

#include "Schedule/Model/Cache/RepeatSchedule.h"

namespace Gs2::Schedule::Model::Cache
{
    FString FRepeatScheduleCache::CreateCacheParentKey(TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset)
    {
        return FString("schedule:") + NamespaceName.Get(FString()) + ":" + UserId.Get(FString()) + ":" + (IsInSchedule.Get(true) ? TEXT("True") : TEXT("False")) + ":" + FString::FromInt(TimeOffset.Get(0)) + ":RepeatSchedule";
    }
    FString FRepeatScheduleCache::CreateCacheKey(TOptional<FString> EventName) { return EventName.Get(FString()); }
    bool FRepeatScheduleCache::TryGet(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, Gs2::Schedule::Model::FRepeatSchedulePtr* Out)
    {
        if (Out) *Out = nullptr;
        if (!Cache.IsValid() || !UserId.IsSet()) return false;
        Gs2::Schedule::Model::FRepeatSchedulePtr Value;
        const bool Found = Cache->TryGet<Gs2::Schedule::Model::FRepeatSchedule>(CreateCacheParentKey(NamespaceName, UserId, IsInSchedule, TimeOffset), CreateCacheKey(EventName), &Value);
        if (Out) *Out = Found ? Value : nullptr;
        return Found;
    }
    void FRepeatScheduleCache::Put(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, const Gs2::Schedule::Model::FRepeatSchedulePtr& Item)
    {
        if (!Cache.IsValid() || !UserId.IsSet()) return;
        Cache->Put(Gs2::Schedule::Model::FRepeatSchedule::TypeName, CreateCacheParentKey(NamespaceName, UserId, IsInSchedule, TimeOffset), CreateCacheKey(EventName), Item, FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
    }
    void FRepeatScheduleCache::Delete(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<FString> EventName, TOptional<int32> TimeOffset)
    {
        if (!Cache.IsValid() || !UserId.IsSet()) return;
        for (const bool IsInSchedule : {false, true}) Cache->Delete(Gs2::Schedule::Model::FRepeatSchedule::TypeName, CreateCacheParentKey(NamespaceName, UserId, TOptional<bool>(IsInSchedule), TimeOffset), CreateCacheKey(EventName));
    }
    Gs2::Core::Model::FGs2ErrorPtr FRepeatScheduleCache::Fetch(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<FString> EventName, TOptional<int32> TimeOffset, const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Schedule::Model::FRepeatSchedulePtr*)>& FetchImpl, Gs2::Schedule::Model::FRepeatSchedulePtr* Out)
    {
        if (Out) *Out = nullptr;
        if (!FetchImpl)
        {
            auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        if (!UserId.IsSet())
        {
            auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Schedule::Model::FRepeatSchedulePtr Item;
        const auto Error = FetchImpl(&Item);
        if (!Error || Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class)) Put(Cache, NamespaceName, UserId, IsInSchedule, EventName, TimeOffset, Item);
        if (!Error) { if (Out) *Out = Item; return nullptr; }
        if (Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            const auto Details = Error->GetErrors();
            if (Details.IsValid() && Details->Num() > 0 && (*Details)[0].IsValid() && (*Details)[0]->GetComponent() == TEXT("event")) return nullptr;
        }
        return Error;
    }
    Gs2::Core::Domain::CallbackID FRepeatScheduleCache::ListSubscribe(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset, TFunction<void(TArray<Gs2::Schedule::Model::FRepeatSchedulePtr>)> Callback)
    {
        if (!Cache.IsValid() || !UserId.IsSet()) return 0;
        return Cache->ListSubscribeTyped(Gs2::Schedule::Model::FRepeatSchedule::TypeName, CreateCacheParentKey(NamespaceName, UserId, IsInSchedule, TimeOffset), [Callback](const TArray<FGs2ObjectPtr>& Values) { TArray<Gs2::Schedule::Model::FRepeatSchedulePtr> Items; for (const auto& Value : Values) if (Value) Items.Add(StaticCastSharedPtr<Gs2::Schedule::Model::FRepeatSchedule>(Value)); if (Callback) Callback(Items); });
    }
    void FRepeatScheduleCache::ListUnsubscribe(const Gs2::Core::Domain::FCacheDatabasePtr& Cache, TOptional<FString> NamespaceName, TOptional<FString> UserId, TOptional<bool> IsInSchedule, TOptional<int32> TimeOffset, Gs2::Core::Domain::CallbackID CallbackID)
    {
        if (!Cache.IsValid() || !UserId.IsSet()) return;
        Cache->ListUnsubscribe(Gs2::Schedule::Model::FRepeatSchedule::TypeName, CreateCacheParentKey(NamespaceName, UserId, IsInSchedule, TimeOffset), CallbackID);
    }
}
