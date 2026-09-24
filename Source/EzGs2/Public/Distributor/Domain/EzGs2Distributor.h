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

#pragma once

#include "CoreMinimal.h"
#include "Distributor/Domain/Gs2Distributor.h"
#include "Util/Net/Gs2Connection.h"
#include "Distributor/Domain/Model/Gs2DistributorEzNamespaceDomain.h"

namespace Gs2::UE5::Distributor::Domain
{
    DECLARE_EVENT_OneParam(Gs2Distributor, FAutoRunStampSheetNotificationEvent, Gs2::Distributor::Model::FAutoRunStampSheetNotificationPtr);
    typedef TSharedPtr<FAutoRunStampSheetNotificationEvent> FAutoRunStampSheetNotificationEventPtr;
    DECLARE_EVENT_OneParam(Gs2Distributor, FAutoRunTransactionNotificationEvent, Gs2::Distributor::Model::FAutoRunTransactionNotificationPtr);
    typedef TSharedPtr<FAutoRunTransactionNotificationEvent> FAutoRunTransactionNotificationEventPtr;

    class EZGS2_API FEzGs2Distributor {
        Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        FAutoRunStampSheetNotificationEvent AutoRunStampSheetNotificationEvent;
        FAutoRunTransactionNotificationEvent AutoRunTransactionNotificationEvent;

        FEzGs2Distributor(
            Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Distributor::Domain::Model::FEzNamespaceDomainPtr Namespace(
            const FString NamespaceName
        ) const;

        FAutoRunStampSheetNotificationEvent& OnAutoRunStampSheetNotification();

        FAutoRunTransactionNotificationEvent& OnAutoRunTransactionNotification();

        // 一括取得（Gs2Distributor:DescribeUserData）でこのユーザーの全データを各モデルのキャッシュへ入れる。ログイン直後に 1 回待つと、
        // 以後の Get / Describe はサーバーへ出ない。キー方式 v2 のプロジェクトでだけ使える。結果はキャッシュへ入れたエントリ数
        class EZGS2_API FLoadUserDataTask final :
            public Gs2::Core::Util::TGs2Future<int32>,
            public TSharedFromThis<FLoadUserDataTask>
        {
            const Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain;
            const Gs2::UE5::Util::FGameSessionPtr GameSession;
        public:
            explicit FLoadUserDataTask(
                const Gs2::Distributor::Domain::FGs2DistributorDomainPtr Domain,
                const Gs2::UE5::Util::FGameSessionPtr GameSession
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<int32>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FLoadUserDataTask>> LoadUserData(
            Gs2::UE5::Util::FGameSessionPtr GameSession
        );
    };
    typedef TSharedPtr<FEzGs2Distributor> FEzGs2DistributorPtr;
}
