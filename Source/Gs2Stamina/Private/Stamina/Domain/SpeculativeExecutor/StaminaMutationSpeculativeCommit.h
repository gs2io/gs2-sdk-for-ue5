#pragma once

#include "CoreMinimal.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Stamina/Model/Cache/Stamina.h"
#include "Stamina/Model/Cache/StaminaModel.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{
    class FStaminaMutationSpeculativeCommit final
    {
    public:
        using FTransform = TFunction<bool(
            const Gs2::Stamina::Model::FStaminaPtr& Item,
            TOptional<int32> MaxCapacity
        )>;

        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& UserId,
            const FString& StaminaName,
            const TOptional<int32>& TimeOffset,
            const FString& ExpectedStaminaId,
            const FString& ExpectedModelId,
            const TOptional<int64>& PreparedRevision,
            const bool UsesMaxCapacity,
            FTransform Transform
        )
        {
            const auto Prepared = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset) + TEXT(":") +
                    Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheKey(StaminaName),
                [Domain, NamespaceName, UserId, StaminaName, TimeOffset, ExpectedStaminaId, ExpectedModelId, PreparedRevision, UsesMaxCapacity, Transform = MoveTemp(Transform)](
                    const TSharedPtr<void>& Current,
                    const bool HasCurrent,
                    TSharedPtr<void>& Next
                ) mutable
                {
                    TOptional<int32> MaxCapacity;
                    if (UsesMaxCapacity)
                        {
                            Gs2::Stamina::Model::FStaminaModelPtr Model;
                            const bool FoundModel = Gs2::Stamina::Model::Cache::FStaminaModelCache::TryGet(
                                Domain->Cache,
                                NamespaceName,
                                StaminaName,
                                TOptional<int32>(),
                                &Model
                            );
                            if (FoundModel && Model.IsValid())
                            {
                                if (!Model->GetStaminaModelId().IsSet() ||
                                    Model->GetStaminaModelId().Get(FString()) != ExpectedModelId ||
                                    !Model->GetName().IsSet() ||
                                    Model->GetName().Get(FString()) != StaminaName)
                                {
                                    Next = nullptr;
                                    return false;
                                }
                                MaxCapacity = Model->GetMaxCapacity();
                            }
                        }

                    Gs2::Stamina::Model::FStaminaPtr Item;
                    if (HasCurrent)
                        {
                            if (!Current.IsValid())
                            {
                                Next = nullptr;
                                return false;
                            }
                            Item = StaticCastSharedPtr<Gs2::Stamina::Model::FStamina>(Current);
                        }
                        else
                        {
                            if (!Gs2::Stamina::Model::Cache::FStaminaCache::TryGet(
                                Domain->Cache,
                                NamespaceName,
                                UserId,
                                StaminaName,
                                TimeOffset,
                                &Item
                            ) || !Item.IsValid() ||
                                !Item->GetStaminaId().IsSet() || Item->GetStaminaId().Get(FString()) != ExpectedStaminaId ||
                                !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
                                !Item->GetStaminaName().IsSet() || Item->GetStaminaName().Get(FString()) != StaminaName ||
                                (Item->GetRevision().Get(0) > 0 &&
                                 (!PreparedRevision.IsSet() || Item->GetRevision().Get(0) != PreparedRevision.Get(0))))
                            {
                                Next = nullptr;
                                return false;
                            }
                        }
                    if (!Item.IsValid() ||
                            !Item->GetStaminaId().IsSet() || Item->GetStaminaId().Get(FString()) != ExpectedStaminaId ||
                            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
                            !Item->GetStaminaName().IsSet() || Item->GetStaminaName().Get(FString()) != StaminaName)
                        {
                            Next = nullptr;
                            return false;
                        }

                    const auto Changed = MakeShared<Gs2::Stamina::Model::FStamina>(*Item);
                    if (!Transform(Changed, MaxCapacity))
                        {
                            Next = nullptr;
                            return false;
                        }
                    if (!Changed->GetStaminaId().IsSet() || Changed->GetStaminaId().Get(FString()) != ExpectedStaminaId ||
                            !Changed->GetUserId().IsSet() || Changed->GetUserId().Get(FString()) != UserId ||
                            !Changed->GetStaminaName().IsSet() || Changed->GetStaminaName().Get(FString()) != StaminaName)
                        {
                            Next = nullptr;
                            return false;
                        }
                    Changed->WithRevision(0);
                    Next = Changed;
                    return true;
                },
                [Domain, NamespaceName, UserId, StaminaName, TimeOffset, ExpectedStaminaId](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid()) return;
                    const auto Item = StaticCastSharedPtr<Gs2::Stamina::Model::FStamina>(State);
                    if (!Item.IsValid() ||
                        !Item->GetStaminaId().IsSet() || Item->GetStaminaId().Get(FString()) != ExpectedStaminaId ||
                        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
                        !Item->GetStaminaName().IsSet() || Item->GetStaminaName().Get(FString()) != StaminaName ||
                        !Item->GetRevision().IsSet() || Item->GetRevision().Get(0) != 0)
                    {
                        return;
                    }
                    Domain->Cache->Put(
                        Gs2::Stamina::Model::FStamina::TypeName,
                        Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheParentKey(NamespaceName, UserId, TimeOffset),
                        Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheKey(StaminaName),
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            );
            return Prepared;
        }

        static int32 Clamp(const int64 Value, const TOptional<int32>& MaxCapacity)
        {
            int64 Result = Value;
            if (MaxCapacity.IsSet() && Result > MaxCapacity.Get(0)) Result = MaxCapacity.Get(0);
            if (Result > TNumericLimits<int32>::Max()) return TNumericLimits<int32>::Max();
            if (Result < TNumericLimits<int32>::Min()) return TNumericLimits<int32>::Min();
            return static_cast<int32>(Result);
        }
    };
}
