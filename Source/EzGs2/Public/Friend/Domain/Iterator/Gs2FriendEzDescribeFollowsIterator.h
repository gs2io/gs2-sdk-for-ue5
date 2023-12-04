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
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

	class EZGS2_API FEzDescribeFollowsIterator :
        public TSharedFromThis<FEzDescribeFollowsIterator>
    {
        Gs2::Friend::Domain::Iterator::FDescribeFollowsIteratorPtr It;
        Gs2::Friend::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        bool WithProfile;

	public:

        explicit FEzDescribeFollowsIterator(
            Gs2::Friend::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            bool WithProfile
        ) :
            It(
                Domain->Follows(
                    WithProfile
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            WithProfile(WithProfile)
        {
        }

		FEzDescribeFollowsIterator(
			const FEzDescribeFollowsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            WithProfile(From.WithProfile)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeFollowsIterator;

			Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FIterator DomainIterator;
			Gs2::UE5::Friend::Model::FEzFollowUserPtr CurrentValue;
        	static Gs2::UE5::Friend::Model::FEzFollowUserPtr ConvertCurrent(
        		Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeFollowsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Friend::Model::FEzFollowUserPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeFollowsIterator> FEzDescribeFollowsIteratorPtr;
}
